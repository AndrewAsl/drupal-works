<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the interesting fields.
 */
function calcmet_form_addarmatura($form, &$form_state) {
  $form = array();
  $entries = calcmet_load('calcmetcat');
  foreach ($entries as $entry) {
    $options[$entry->ccid] = t("@ccid: @title",
      array(
        '@ccid' => $entry->ccid,
        '@title' => $entry->title,
      )
    );
  }
  ksort($options);
  firep($options);
  //$options_first = $options;
  // If we have a value for the first dropdown from $form_state['values'] we use
  // this both as the default value for the first dropdown and also as a
  // parameter to pass to the function that retrieves the options for the
  // second dropdown.
  if (isset($form_state['values']['dropdown_first'])){
     $str = explode(':', $form_state['values']['dropdown_first'], 0); 
  }
  $selected =  isset($form_state['values']['dropdown_first'])? $str[0] : key($options);
  firep($selected);
  $form['dropdown_first'] = array(
    '#type' => 'select',
    '#title' => 'Category name',
    '#options' => $options,
    '#default_value' => $selected,
    // Bind an ajax callback to the change event (which is the default for the
    // select form type) of the first dropdown. It will replace the second
    // dropdown when rebuilt.
    '#ajax' => array(
      // When 'event' occurs, Drupal will perform an ajax request in the
      // background. Usually the default value is sufficient (eg. change for
      // select elements), but valid values include any jQuery event,
      // most notably 'mousedown', 'blur', and 'submit'.
      // 'event' => 'change',
      'callback' => 'ajax_example_dependent_dropdown_callback',
      'wrapper' => 'dropdown-second-replace',
    ),
  );

  $form['dropdown_second'] = array(
    '#type' => 'select',
    '#title' => $selected . ' ' . t('Категория'),
      
    // The entire enclosing div created here gets replaced when dropdown_first
    // is changed.
    '#prefix' => '<div id="dropdown-second-replace">',
    '#suffix' => '</div>',
    // When the form is rebuilt during ajax processing, the $selected variable
    // will now have the new value and so the options will change.
    '#options' => _calcmet_get_second_dropdown_options($selected),
    //'#options' => array (1, 2, 3, 4),
    '#default_value' => isset($form_state['values']['dropdown_second']) ? $form_state['values']['dropdown_second'] : '',
  );
  
  $form['armaturadata'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по арматуре'),
  );
  $form['armaturadata']['diametr'] = array(
    '#type'  => 'textfield',
    '#title' => t('Диаметр'),
    '#size'  => 60,
  );
  $form['armaturadata']['csa'] = array(
    '#type'  => 'textfield',
    '#title' => t('Площадь поперечного сечения, см2'),
    '#size'  => 60,
  );
  $form['armaturadata']['massonem'] = array(
    '#type'  => 'textfield',
    '#title' => t('Масса 1 м, кг'),
    '#size'  => 60,
  );
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function __ajax_example_dependent_dropdown_callback($form, $form_state) {
  return $form['dropdown_second'];
  //dd($form_state); 
}

function _calcmet_get_second_dropdown_options($key = '') {
  $entries = db_select('calcmetundercat', 'uc')
            -> fields('uc')
            -> condition ('uc.ccid', $key)
            -> execute()
            -> fetchAll();
  //dsm($entries);
  foreach ($entries as $entry) {
    $options[$entry->cucid] = t("@cucid: @title",
      array(
        '@cucid' => $entry->cucid,
        '@title' => $entry->title,
      )
    );
  }
  //ksort($options);
  
  if (isset($options)) {
    return $options;
  }
  else {
    return '';
  }
}

function calcmet_form_addarmatura_submit($form, &$form_state) {  
  // Save the submitted entry.
  //dsm($form_state);  
  $basename = 'calcmetarmatura';
  if(!empty($form_state['values']['diametr'] && $form_state['values']['csa'] && $form_state['values']['massonem'])){
      $entry = array(
        'ccid'  => $form_state['values']['dropdown_first'],  
        'cucid'  => $form_state['values']['dropdown_second'] ? $form_state['values']['dropdown_second'] : 0,  
        'diametr' => $form_state['values']['diametr'],
        'csa' => $form_state['values']['csa'], 
        'massonem' => $form_state['values']['massonem'], 
      );
  } else {
      drupal_set_message ('Введите данные');
  }   
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}