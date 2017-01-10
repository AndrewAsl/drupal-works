<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Шапка
 */
function set_tube_page(){
    $output = '';
    $output .= render(drupal_get_form('calcmet_undercat_form'));
    $output .= render(drupal_get_form('calcmet_tube_bezshov_form'));
    $output .= render(drupal_get_form('tube_spec_form'));
    //$output .= '</div>';
    return $output;
}
function calcmet_undercat_form($form, &$form_state){
    $form['cat'] = array(
        '#title' => t('Категория проката'),
        '#type' => 'select',
        '#options' => calcmet_get_undercategory_title('calcmetundercat'),
        '#default_value' => 5,
        //'#size' => 10,
        '#description' => t('Выберите тип стального проката'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_change_cat',
//        ),
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>'  
    );
    $form_state['rebuild'] = TRUE;
    return $form;
}

/*
    Раздел по квадрату
 */
function calcmet_tube_form($form, &$form_state){
    $form = array();
    
    $form['tube'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['tube']['shovnames'] = array(
        '#title' => t('Название, наружный диаметр х толщину'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmettubestellsvarnpryamoshovn'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип трубы'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'tube_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['tube']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['tube']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['tube']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м<sup>2</sup>'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['tube']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/a.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['tube']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="tube-info">'
        . '<strong>Наружный диаметр, мм:</strong> <span id="diametr">12</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">0.8</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.221</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 10704-91 "Трубы стальные электросварные прямошовные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3, с учетом изменения №2'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['tube']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmettube.js',
    );
    $form['#action'] = url('/services/calcmet/tube');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_tube_bezshov_form($form, &$form_state){
    $form = array();    
    
    $form['tube'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['tube']['bezshvov'] = array(
        '#title' => t('Название, наружный диаметр х толщину стенки'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmettubessteelwithoutseam'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'tube_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['tube']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['tube']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['tube']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['tube']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/a.jpg" width = 250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['tube']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="tube-info">'
        . '<strong>Наружный диаметр, мм:</strong> <span id="diametr">20</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">2.5</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">1.08</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8732-78 "Трубы стальные бесшовные горячедеформированные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3 с учетом изменения №2 '
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['tube']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
   
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmettube.js',
    );
    $form['#action'] = url('/services/calcmet/tube');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_tube_kvadrat_form($form, &$form_state){
    $form = array();    
    
    $form['tube'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['tube']['kvnames'] = array(
        '#title' => t('Название, сторона квадрата х тощину стенки'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmettubessteelkvadrat'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'tube_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['tube']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['tube']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['tube']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['tube']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/tubekvad.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['tube']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="tube-info">'
        . '<strong>Наружный размер, мм:</strong> <span id="diametr">10</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">0.8</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">0.283</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.222</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8639-82 "Трубы стальные квадратные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3 с учетом изменения №4'
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',       
    );
    $form['tube']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
   
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmettube.js',
    );
    $form['#action'] = url('/services/calcmet/tube');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_tube_oval_form($form, &$form_state){
    $form = array();    
    
    $form['tube'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['tube']['ovalnames'] = array(
        '#title' => t('Название, сторона 1 х сторона 2 х толщина стенки'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmettubessteeloval'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'tube_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['tube']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['tube']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['tube']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['tube']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/tubeoval.jpg" width=250px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['tube']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="tube-info">'
        . '<strong>Размер 1, мм:</strong> <span id="razmer1">6</span><br>'
        . '<strong>Размер 2, мм:</strong> <span id="razmer2">3</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">0.5</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">0.0653</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.0513</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8642-68 "Трубы стальные овальные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3 с учетом изменения №1 '
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['tube']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmettube.js',
    );
    $form['#action'] = url('/services/calcmet/tube');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */
function calcmet_tube_ugol_form($form, &$form_state){
    $form = array();    
    
    $form['tube'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone">',
        '#suffix' =>'</div>'  
    );
    
    
    $form['tube']['ugolnames'] = array(
        '#title' => t('Название, сторона1 х сторона2 х толщина стенки'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmettubessteelugol'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'tube_change_info',
        ),*/
        '#prefix' => '<div id="ajaxoptions" class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['tube']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'tube_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['tube']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['tube']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['tube']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/tubeugol.jpg" width=250px ></div>',
        '#prefix' => '<div class = "col-md-4 clearfix">',
        '#suffix' =>'</div>'
    );
    
    $form['tube']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="tube-info">'
        . '<strong>Размер 1, мм:</strong> <span id="razmer1">15</span><br>'
        . '<strong>Размер 2, мм:</strong> <span id="razmer2">10</span><br>'
        . '<strong>Толщина стенки, мм:</strong> <span id="thickness">1.0</span><br>'
        . '<strong>Площадь поперечного сечения, см2:</strong> <span id="csa">0.443</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.348</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 8645-68 "Трубы стальные прямоугольные. Сортамент" '
        . 'утвержден постановлением Госстандарта Республики Беларусь от 17.12.1992 г. № 3 с учетом изменения №4 '
        .'</div>',
        '#prefix' => '<div class="row"><div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['tube']['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div></div>',        
    );
    
    
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmettube.js',
    );
    $form['#action'] = url('/services/calcmet/tube');
    $form_state['rebuild'] = TRUE;
    return $form;
}
/*
 * Конец формы для двутавра
 */

function tube_spec_form($form, &$form_state){
    $form['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    return $form;
}

function tube_change_info(){
    $select = $_POST['option'];
    $basename = $_POST['tubename'];
    //dsm($select);
    switch ($basename) {
        case 'shov':
            $infos = db_select('calcmettubestellsvarnpryamoshovn', 'sh')
                ->fields('sh', array('tsshdiametr', 'tsshthickness', 'massonem', 'drawonemetr'))
                ->condition('sh.tsshdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->tsshdiametr;
            $thick = $infos[0]->tsshthickness;
            $csa = $infos[0]->drawonemetr;
            $massonem = $infos[0]->massonem;
        break;
        case 'bezshvov':
            $infos = db_select('calcmettubessteelwithoutseam', 'tws')
                ->fields('tws', array('tswsdiametr', 'tswsthickness', 'massonem', 'drawonemetr'))
                ->condition('tws.tswsdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->tswsdiametr;
            $thick = $infos[0]->tswsthickness;
            $csa = $infos[0]->drawonemetr;
            $massonem = $infos[0]->massonem;
        break;
        case 'tubekvadrat':
            $infos = db_select('calcmettubessteelkvadrat', 'tkv')
                ->fields('tkv', array('tskvstorona', 'tskvthickness', 'massonem', 'drawonemetr'))
                ->condition('tkv.tskvdid', $select)
                ->execute()
                ->fetchAll();
            $diametr = $infos[0]->tskvstorona;
            $thick = $infos[0]->tskvthickness;
            $csatext = $infos[0]->drawonemetr;
            $massonem = $infos[0]->massonem;
            $csa = $diametr * 4 * 0.001; 
        break;
        case 'tubeoval':
            $infos = db_select('calcmettubessteeloval', 'tov')
                ->fields('tov', array('tsovstorona1', 'tsovstorona2', 'tsovthickness', 'massonem', 'drawonemetr'))
                ->condition('tov.tsovdid', $select)
                ->execute()
                ->fetchAll();
            $storona1 = $infos[0]->tsovstorona1;
            $storona2 = $infos[0]->tsovstorona2;
            $thick = $infos[0]->tsovthickness;
            $csatext = $infos[0]->drawonemetr;
            $massonem = $infos[0]->massonem;
            $csa = ($storona1*0.5 + $storona2*0.5)*0.001*3.14; 
        break;
        case 'tubeugol':
            $infos = db_select('calcmettubessteelugol', 'tug')
                ->fields('tug', array('tsugstorona1', 'tsugstorona2', 'tsugthickness', 'massonem', 'drawonemetr'))
                ->condition('tug.tsugdid', $select)
                ->execute()
                ->fetchAll();
            $storona1 = $infos[0]->tsugstorona1;
            $storona2 = $infos[0]->tsugstorona2;
            $thick = $infos[0]->tsugthickness;
            $csatext = $infos[0]->drawonemetr;
            $massonem = $infos[0]->massonem;
            $csa = ($storona1 + $storona2)*0.001*2; 
        break;

        default:
        break;
    }
    drupal_json_output(array(                       
                'diametr'=> $diametr,                       
                'thick'=> $thick,                       
                'storona1'=> ($storona1)? $storona1 : '',                       
                'storona2'=> ($storona2)? $storona2 : '',                                            
                'csatext'=> ($csatext)? $csatext : '',                       
                'csa'=> $csa,                       
                'massonem'=> $massonem,                       
                ));       
    drupal_exit();
}

function calcmet_get_undercategory_title($basename){
     $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetundercat':
                if ($entry->ccid == 7){
                    $options[$entry->cucid] = $entry->title;
                }
                break;
            default:
                break;
        }
    }
    return $options;
}

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmettubestellsvarnpryamoshovn':
                $options[$entry->tsshdid] = $entry->tsshname;
                break;
            case 'calcmettubessteelwithoutseam':
                $options[$entry->tswsdid] = $entry->tswsname;
                break;
            case 'calcmettubessteelkvadrat':
                $options[$entry->tskvdid] = $entry->tskvname;
                break;
            case 'calcmettubessteeloval':
                $options[$entry->tsovdid] = $entry->tsovname;
                break;
            case 'calcmettubessteelugol':
                $options[$entry->tsugdid] = $entry->tsugname;
                break;
            default:
                break;
        }
    }
    return $options;
}

function tube_change_options(){
    $select = $_POST['ajaxtubechangeoptions'];
    switch ($select) {
            case 5:
                $form = drupal_render(drupal_get_form('calcmet_tube_bezshov_form'));                
                break;
            case 6:
                $form = drupal_render(drupal_get_form('calcmet_tube_form'));
                break;
            case 7:
                $form = drupal_render(drupal_get_form('calcmet_tube_kvadrat_form'));
                break;
            case 8:
                $form = drupal_render(drupal_get_form('calcmet_tube_oval_form'));
                break;
            case 9:
                $form = drupal_render(drupal_get_form('calcmet_tube_ugol_form'));
                break;

            default:
                break;
        }
    drupal_json_output($form);
    //return $form;
    drupal_exit();
}